document.addEventListener("DOMContentLoaded", async () => {
  const token = localStorage.getItem("authToken");
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
	
  const nameInput = document.getElementById("name");
  const surnameInput = document.getElementById("surname");
  const emailInput = document.getElementById("email");
  const passwordInput = document.getElementById("password");
  const confirmPasswordInput = document.getElementById("confirmPassword");
  const ageInput = document.getElementById("age");

  // Başta input'ları pasifleştir
  disableInputs();
	
  try {
    const res = await fetch("https://dip392-etik.onrender.com/api/users/me", {
      headers: { Authorization: `Bearer ${token}` }
    });

    if (!res.ok) throw new Error("Failed to fetch user info");

    const data = await res.json();

    // Formu doldur
    nameInput.value = data.name;
    surnameInput.value = data.surname;
    emailInput.value = data.email;
    passwordInput.value = ""; // güvenlik için boş
    confirmPasswordInput.value = "";

    // Yaşı hesapla (birthday -> YYYY-MM-DD)
    const birthday = new Date(data.birthday);
    const today = new Date();
    let age = today.getFullYear() - birthday.getFullYear();
    if (
      today.getMonth() < birthday.getMonth() ||
      (today.getMonth() === birthday.getMonth() && today.getDate() < birthday.getDate())
    ) {
      age--;
    }
    ageInput.value = age;

  } catch (err) {
    console.error("Kullanıcı verisi alınamadı:", err);
    logout();
  }
});

function enableEdit() {
  const inputs = document.querySelectorAll(".account-container input");
  inputs.forEach(input => input.disabled = false);
}

function disableInputs() {
  const inputs = document.querySelectorAll(".account-container input");
  inputs.forEach(input => input.disabled = true);
}

async function saveAccount() {
  const token = localStorage.getItem("authToken");
  if (!token) {
    window.location.href = "signin.html";
    return;
  }

  const name = document.getElementById("name").value.trim();
  const surname = document.getElementById("surname").value.trim();
  const email = document.getElementById("email").value.trim();
  const password = document.getElementById("password").value;
  const confirmPassword = document.getElementById("confirmPassword").value;

  if (password && password !== confirmPassword) {
    alert("Passwords do not match.");
    return;
  }

  try {
    const res = await fetch("https://dip392-etik.onrender.com/api/users/me", {
      method: "PUT",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${token}`
      },
      body: JSON.stringify({
        name,
        surname,
        email,
        ...(password ? { password } : {}) // password boş değilse gönder
      })
    });

    const data = await res.json();

    if (!res.ok) {
      alert("Update failed: " + (data.message || "Unknown error"));
    } else {
      alert("Account info updated successfully.");
      disableInputs();
    }

  } catch (err) {
    console.error("Update error:", err);
    alert("Something went wrong.");
  }
}

function logout() {
  localStorage.removeItem("authToken");
  window.location.href = "signin.html";
}