document.getElementById("signinForm").addEventListener("submit", async function (e) {
  e.preventDefault();

  const form = e.target;

  const credentials = {
    email: form.email.value.trim(),
    password: form.password.value
  };

  try {
    const response = await fetch("https://dip392-etik.onrender.com/api/auth/signin", {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify(credentials)
    });

    const data = await response.json();

    if (response.ok) {
      // Token ve kullanıcı ID'sini kaydet
		localStorage.setItem("authToken", data.token);
		localStorage.setItem("userId", data.user.id);
		const fullName = [data.user.name, data.user.surname].filter(Boolean).join(" ");
		localStorage.setItem("userFullName", fullName);
      
      // Anasayfaya yönlendir
      window.location.href = "index.html";
    } else {
      alert("Sign in failed: " + (data.message || "Unknown error"));
    }

  } catch (error) {
    alert("Network error: " + error.message);
  }
});
