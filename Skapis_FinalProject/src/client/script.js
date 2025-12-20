document.addEventListener("DOMContentLoaded", async () => {
  const token = localStorage.getItem("authToken");
  if (!token) {
    window.location.href = "signin.html";
    return;
  }

  // Kullanıcı adını backend'den al ve göster
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

  // Ürünleri backend'den çek ve göster
  try {
    const response = await fetch("https://dip392-etik.onrender.com/api/products", {
      method: "GET",
      headers: {
        Authorization: `Bearer ${token}`
      }
    });

    if (!response.ok) {
      throw new Error("Unauthorized or failed to fetch products.");
    }

    const products = await response.json();
    renderProducts(products);

  } catch (error) {
    alert("Session expired or failed to fetch products.");
    logout();
  }
});

function renderProducts(products) {
  const sliders = document.querySelectorAll(".slider");
  sliders.forEach(slider => slider.innerHTML = ""); // temizle

  products.forEach(product => {
    const card = document.createElement("div");
    card.className = "frame";

    card.innerHTML = `
      <img src="${product.imageUrl}" alt="${product.name}" style="width: 120px; height: 110px; object-fit: contain; margin-bottom: 2px;">
      <p><strong>${product.name}</strong><br>$${product.price.toFixed(2)}<br>From ${product.owner?.name || "Unknown Store"}</p>
      <button class="btn-buy" onclick="buyProduct('${product._id}')">BUY</button>
      <button class="btn-negotiate" onclick="negotiateProduct('${product._id}')">NEGOTIATE</button>
    `;

    sliders[0].appendChild(card); // ilk slider'a ekle
  });
  const slider = sliders[0];
    const prevBtn = document.getElementById("prevBtn");
    const nextBtn = document.getElementById("nextBtn");

    if (prevBtn && nextBtn && slider) {
      prevBtn.addEventListener("click", () => {
        slider.scrollBy({ left: -300, behavior: "smooth" });
      });

      nextBtn.addEventListener("click", () => {
        slider.scrollBy({ left: 300, behavior: "smooth" });
      });

      setInterval(() => {
        const maxScrollLeft = slider.scrollWidth - slider.clientWidth;

        if (Math.ceil(slider.scrollLeft) >= maxScrollLeft) {
          slider.scrollTo({ left: 0, behavior: "smooth" });
        } else {
          slider.scrollBy({ left: 300, behavior: "smooth" });
        }
      }, 2000);
    }
}

async function buyProduct(productId) {
  const token = localStorage.getItem("authToken");
  if (!token) {
    alert("Please sign in to add to cart.");
    window.location.href = "signin.html";
    return;
  }

  try {
    const res = await fetch("https://dip392-etik.onrender.com/api/cart", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${token}`
      },
      body: JSON.stringify({ productId })
    });

    const data = await res.json();

    if (res.ok) {
      alert("Added to cart!");
    } else {
      alert("Failed to add: " + (data.message || "Unknown error"));
    }

  } catch (err) {
    console.error("Add to cart error:", err);
    alert("Something went wrong.");
  }
}
async function negotiateProduct(productId) {
  const token = localStorage.getItem("authToken");
  if (!token) {
    alert("Please sign in to negotiate.");
    return;
  }

  const input = prompt("Enter your offer price:");
  const offeredPrice = parseFloat(input);

  if (isNaN(offeredPrice) || offeredPrice <= 0) {
    alert("Invalid price. Please enter a valid number.");
    return;
  }

  try {
    const res = await fetch("https://dip392-etik.onrender.com/api/negotiations", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${token}`
      },
      body: JSON.stringify({
        productId: productId,
        offeredPrice: offeredPrice
      })
    });

    const data = await res.json();

    if (res.ok) {
      alert("Offer sent! We'll notify you if it's accepted.");
    } else {
      alert("Failed to send offer: " + (data.message || "Unknown error"));
    }

  } catch (error) {
    console.error("Negotiation error:", error);
    alert("Failed to send negotiation request.");
  }
}
function logout() {
  localStorage.removeItem("authToken");
  localStorage.removeItem("userId");
  window.location.href = "signin.html";
}

