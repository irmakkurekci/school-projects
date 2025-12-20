document.getElementById("signupForm").addEventListener("submit", async function (e) {
  e.preventDefault();

  const form = e.target;

  const userData = {
    name: form.name.value.trim(),
    surname: form.surname.value.trim(),
    birthday: form.birthday.value,
    phone: form.phone.value.trim(),
    email: form.email.value.trim(),
    password: form.password.value
  };

  try {
    const response = await fetch("https://dip392-etik.onrender.com/api/auth/signup", {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify(userData)
    });

    const data = await response.json();

    if (response.ok) {
      // Token'ı kaydet
		localStorage.setItem("authToken", data.token);
		localStorage.setItem("userId", data.user.id);
		const fullName = [data.user.name, data.user.surname].filter(Boolean).join(" ");
		localStorage.setItem("userFullName", fullName);
      
      // Kullanıcıyı yönlendir (örnek: index.html, istersen değiştir)
      window.location.href = "index.html";
    } else {
      alert("Sign up failed: " + (data.message || "Unknown error"));
    }

  } catch (error) {
    alert("Network error: " + error.message);
  }
});
