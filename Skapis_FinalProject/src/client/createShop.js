let token = "";
let storeId = "";
let editingProductId = null;
// Sayfa yüklendiğinde token kontrol + mağaza kontrol + ürün yükleme
document.addEventListener("DOMContentLoaded", async () => {
  token = localStorage.getItem("authToken");
  if (!token) {
    window.location.href = "signin.html";
    return;
  }
  try {
    const userRes = await fetch("https://dip392-etik.onrender.com/api/users/me", {
      method: "GET",
      headers: {
        Authorization: `Bearer ${token}`
      }
    });

    if (userRes.ok) {
      const userData = await userRes.json();
      const fullName = `${userData.name} ${userData.surname}`;

      const userIcon = document.querySelector(".dropdown");
      const nameDiv = document.createElement("div");
      nameDiv.textContent = fullName;
      nameDiv.style.marginTop = "5px";
      nameDiv.style.color = "#FF1493";
      nameDiv.style.fontWeight = "bold";
      nameDiv.style.fontSize = "14px";
      nameDiv.style.textAlign = "center";
      userIcon.appendChild(nameDiv);
    } else {
      throw new Error("Failed to fetch user info");
    }
  } catch (error) {
    console.error("User fetch error:", error);
    logout();
    return;
  }

  try {
    const res = await fetch("https://dip392-etik.onrender.com/api/stores/me", {
      headers: { Authorization: `Bearer ${token}` }
    });

    if (res.ok) {
      const store = await res.json();
      storeId = store._id;
      document.getElementById("shopTitle").textContent = `Your Shop: ${store.name}`;
	  document.getElementById("shopSection").classList.remove("hidden");
	  await loadMyProducts();
	  await loadDashboard(); // ✅ DASHBOARD YÜKLENİYOR
	  await loadNegotiationsForSeller(); // ✅ TEKLİFLERİ YÜKLE
    } else {
      alert("You must create a shop first.");
    }

  } catch (err) {
    console.error("Error getting shop:", err);
    alert("Error loading shop info.");
  }
});
async function createShop() {
  const shopName = prompt("Enter your shop name:");
  if (!shopName || shopName.trim() === "") {
    alert("Shop name is required.");
    return;
  }

  try {
    const response = await fetch("https://dip392-etik.onrender.com/api/stores", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${token}`
      },
      body: JSON.stringify({ name: shopName })
    });

    if (response.ok) {
      const newStore = await response.json();
      alert("Shop created successfully!");
      window.location.reload(); // mağaza yaratıldıktan sonra sayfayı yenile
    } else {
      const data = await response.json();
      alert("Error creating shop: " + (data.message || "Unknown error"));
    }
  } catch (err) {
    console.error("Create shop error:", err);
    alert("Server error while creating shop.");
  }
}
async function addProduct() {
  const name = document.getElementById("productName").value.trim();
  const description = document.getElementById("productDescription").value.trim();
  const price = parseFloat(document.getElementById("productPrice").value);
  const imageUrl = document.getElementById("productImage").value.trim();
  const inStock = document.getElementById("productStock").checked;

  if (!name || isNaN(price)) {
    alert("Please fill out product name and price.");
    return;
  }

  try {
    const res = await fetch("https://dip392-etik.onrender.com/api/products", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${token}`
      },
      body: JSON.stringify({
        name,
        description,
        price,
        imageUrl,
        inStock,
        store: storeId
      })
    });

    if (res.ok) {
      alert("Product added.");
      clearProductForm();
      await loadMyProducts();
    } else {
      const data = await res.json();
      alert("Add failed: " + (data.message || "Unknown error"));
    }

  } catch (err) {
    console.error("Add product error:", err);
    alert("Server error.");
  }
}

function clearProductForm() {
  document.getElementById("productName").value = "";
  document.getElementById("productDescription").value = "";
  document.getElementById("productPrice").value = "";
  document.getElementById("productImage").value = "";
  document.getElementById("productStock").checked = false;
}
let currentProducts = []; // dışarıda tanımlanmalı
async function loadMyProducts() {
  try {
    const res = await fetch("https://dip392-etik.onrender.com/api/products/my-products", {
      headers: { Authorization: `Bearer ${token}` }
    });

    const products = await res.json();
    currentProducts = products; // doğru yere aldık ✅

    const productList = document.getElementById("productList");
    productList.innerHTML = "";

    products.forEach(prod => {
      const item = document.createElement("div");
      item.className = "product-item";
	  item.innerHTML = `
	    <strong>${prod.name}</strong> - $${prod.price.toFixed(2)}<br>
	    <em>${prod.description || ""}</em><br>
	    <button class="btn" onclick="editProduct('${prod._id}')">Edit</button>
	    <button class="btn" onclick="deleteProduct('${prod._id}')">Delete</button>
	    <hr>
	  `;
      productList.appendChild(item);
    });

  } catch (err) {
    console.error("loadMyProducts error:", err);
  }
}

async function deleteProduct(id) {
  if (!confirm("Delete this product?")) return;

  try {
    const res = await fetch(`https://dip392-etik.onrender.com/api/products/${id}`, {
      method: "DELETE",
      headers: { Authorization: `Bearer ${token}` }
    });

    if (res.ok) {
      alert("Product deleted.");
      await loadMyProducts();
    } else {
      alert("Delete failed.");
    }
  } catch (err) {
    console.error("Delete error:", err);
  }
}

function editProduct(id) {
  const product = currentProducts.find(p => p._id === id);
  if (!product) return;

  editingProductId = id;

  // Formu doldur
  document.getElementById("productName").value = product.name;
  document.getElementById("productDescription").value = product.description || "";
  document.getElementById("productPrice").value = product.price;
  document.getElementById("productImage").value = product.imageUrl || "";
  document.getElementById("productStock").checked = product.inStock;

  // Butonları değiştir
  document.querySelector("button[onclick='addProduct()']").classList.add("hidden");
  document.getElementById("updateBtn").classList.remove("hidden");
}
async function updateProduct() {
  if (!editingProductId) return;

  const name = document.getElementById("productName").value.trim();
  const description = document.getElementById("productDescription").value.trim();
  const price = parseFloat(document.getElementById("productPrice").value);
  const imageUrl = document.getElementById("productImage").value.trim();
  const inStock = document.getElementById("productStock").checked;

  if (!name || isNaN(price)) {
    alert("Please fill out name and price.");
    return;
  }

  try {
    const res = await fetch(`https://dip392-etik.onrender.com/api/products/${editingProductId}`, {
      method: "PUT",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${token}`
      },
      body: JSON.stringify({ name, description, price, imageUrl, inStock })
    });

    if (res.ok) {
      alert("Product updated.");
      editingProductId = null;
      clearProductForm();
      document.getElementById("updateBtn").classList.add("hidden");
      document.querySelector("button[onclick='addProduct()']").classList.remove("hidden");
      await loadMyProducts();
    } else {
      const data = await res.json();
      alert("Update failed: " + (data.message || "Unknown error"));
    }

  } catch (err) {
    console.error("Update error:", err);
  }
}
async function loadDashboard() {
  try {
    const res = await fetch("https://dip392-etik.onrender.com/api/seller/dashboard", {
      headers: { Authorization: `Bearer ${token}` }
    });

    if (!res.ok) throw new Error("Unauthorized");

    const data = await res.json();

    document.getElementById("totalSales").textContent = data.totalSales || 0;
    document.getElementById("totalRevenue").textContent = (data.totalRevenue || 0).toFixed(2);

    const soldList = document.getElementById("soldProductsList");
    soldList.innerHTML = "";

    data.soldProducts.forEach(p => {
      const li = document.createElement("li");
      li.textContent = `${p.name} - $${p.price.toFixed(2)} (Sold to ${p.buyer?.name || "unknown"})`;
      soldList.appendChild(li);
    });

    const offersList = document.getElementById("offersList");
    offersList.innerHTML = "";

    data.offers.forEach(o => {
      const li = document.createElement("li");
      li.textContent = `Offer on ${o.product?.name || "unknown"}: $${o.price} from ${o.buyer?.email || "someone"}`;
      offersList.appendChild(li);
    });

  } catch (err) {
    console.error("Dashboard load error:", err);
  }
}

async function loadNegotiationsForSeller() {
  const token = localStorage.getItem("authToken");
  if (!token) return;

  try {
    // Kullanıcı bilgisi (kendi ID'mizi almak için)
    const userRes = await fetch("https://dip392-etik.onrender.com/api/users/me", {
      headers: { Authorization: `Bearer ${token}` }
    });
    const userData = await userRes.json();
    const myUserId = userData._id;

    // Negotiation'ları çek
    const res = await fetch("https://dip392-etik.onrender.com/api/negotiations/me", {
      headers: { Authorization: `Bearer ${token}` }
    });
    const negotiations = await res.json();

    const container = document.getElementById("offersContainer");
    container.innerHTML = "";

    if (!negotiations.length) {
      container.innerHTML = "<p>No negotiation offers yet.</p>";
      return;
    }

    for (const offer of negotiations) {
      // Ürünü detaylı çek (teklif edilen ürün)
      const prodRes = await fetch(`https://dip392-etik.onrender.com/api/products/${offer.product}`);
      const product = await prodRes.json();
	  console.log("Owner for product:", product.owner);
      // Sadece bana ait ürünleri göster
	  if (
	    product.owner === myUserId ||           // string eşleşme
	    product.owner?._id === myUserId         // object ise
	  ) {
	    const item = document.createElement("div");
	    item.className = "offer-item";
	    item.innerHTML = `
	      <p><strong>Product:</strong> ${product.name}</p>
	      <p><strong>Offered Price:</strong> $${offer.offeredPrice}</p>
	      <p><strong>Status:</strong> ${offer.status}</p>
	      ${offer.status === "pending" ? `
	        <button class="btn" onclick="respondNegotiation('${offer._id}', 'accepted')">Accept</button>
	        <button class="btn" onclick="respondNegotiation('${offer._id}', 'rejected')">Reject</button>
	      ` : ""}
	    `;
	    container.appendChild(item);
	  }
    }

  } catch (err) {
    console.error("Negotiation fetch error:", err);
  }
}