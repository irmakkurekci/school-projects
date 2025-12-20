let token = localStorage.getItem("authToken");
if (!token) window.location.href = "signin.html";

document.addEventListener("DOMContentLoaded", loadCart);

async function loadCart() {
  try {
    const res = await fetch("https://dip392-etik.onrender.com/api/cart", {
      headers: { Authorization: `Bearer ${token}` }
    });

    const items = await res.json();
    const container = document.getElementById("cartItems");
    container.innerHTML = "";

    if (!items.length) {
      container.innerHTML = "<p>Your cart is empty.</p>";
      return;
    }

    items.forEach(item => {
      const product = item.product;
      if (!product) return;

      const div = document.createElement("div");
      div.className = "cart-item";
      div.innerHTML = `
        <img src="${product.imageUrl}" alt="${product.name}">
        <div class="item-info">
          <p><strong>${product.name}</strong></p>
          <p>$${product.price.toFixed(2)}</p>
        </div>
        <button class="remove-btn" onclick="removeFromCart('${item._id}')">Remove</button>
      `;
      container.appendChild(div);
    });

  } catch (err) {
    console.error("Failed to load cart", err);
  }
}
async function removeFromCart(id) {
  try {
    const res = await fetch(`https://dip392-etik.onrender.com/api/cart/${id}`, {
      method: "DELETE",
      headers: { Authorization: `Bearer ${token}` }
    });

    if (res.ok) {
      loadCart();
    } else {
      alert("Failed to remove item.");
    }
  } catch (err) {
    console.error("Remove error", err);
  }
}

async function purchaseCart() {
  if (!confirm("Are you sure you want to purchase all items in your cart?")) return;

  try {
    const res = await fetch("https://dip392-etik.onrender.com/api/orders/from-cart", {
      method: "POST",
      headers: { Authorization: `Bearer ${token}` }
    });

    const data = await res.json();

    if (res.ok) {
      alert("Purchase successful!");
      loadCart();
    } else {
      alert("Purchase failed: " + (data.message || "Unknown error"));
    }

  } catch (err) {
    console.error("Purchase error", err);
  }
}