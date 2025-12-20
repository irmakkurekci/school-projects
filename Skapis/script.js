// Sign-up Sign in Window
		function calculateAge(birthday) {
            const birthDate = new Date(birthday);
            const today = new Date();
            let age = today.getFullYear() - birthDate.getFullYear();
            const m = today.getMonth() - birthDate.getMonth();
            if (m < 0 || (m === 0 && today.getDate() < birthDate.getDate())) {
                age--;
            }
            return age;
        }
        document.getElementById("signupForm").addEventListener("submit", function (e) {
            e.preventDefault();
            const birthday = document.getElementById("birthday").value;
            const age = calculateAge(birthday);
            if (age < 16) {
                alert("You must be at least 16 years old to sign up.");
                return;
            }
            alert("Your account has been created!");
            document.getElementById("popup").style.display = "none";
            document.getElementById("main-content").style.display = "block";
        });

        document.getElementById("signinForm").addEventListener("submit", function (e) {
            e.preventDefault();
            document.getElementById("popup").style.display = "none";
            document.getElementById("main-content").style.display = "block";
        });

        document.getElementById("switchToSignin").addEventListener("click", function () {
            document.getElementById("signupForm").style.display = "none";
            document.getElementById("signinForm").style.display = "block";
        });


// Auto-scroll sliders
setInterval(() => {
  document.querySelectorAll('.slider').forEach(slider => {
    slider.scrollBy({ left: 220, behavior: 'smooth' });
  });
}, 3000);

// Manual scroll buttons
document.querySelectorAll('.slider-container').forEach(container => {
  const slider = container.querySelector('.slider');
  const btnLeft = container.querySelector('.slider-btn.left');
  const btnRight = container.querySelector('.slider-btn.right');

  btnRight.addEventListener('click', () => {
    slider.scrollBy({ left: 220, behavior: 'smooth' });
  });

  btnLeft.addEventListener('click', () => {
    slider.scrollBy({ left: -220, behavior: 'smooth' });
  });
});

// Open product detail page
document.querySelectorAll('.frame').forEach(frame => {
  frame.addEventListener('click', () => {
    const id = frame.getAttribute('data-id');
    if (id) {
      window.location.href = `product.html?item=${id}`;
    }
  });
});

        // Product Modal Logic
        function showProductModal(imgSrc, desc, price, shop) {
            document.getElementById('modalImage').src = imgSrc;
            document.getElementById('modalDescription').textContent = desc;
            document.getElementById('modalPrice').textContent = price;
            document.getElementById('modalShop').textContent = shop;
            document.getElementById('productModal').style.display = 'flex';
        }

        // Example: Attach to all frames dynamically later
        document.addEventListener("DOMContentLoaded", function() {
            document.querySelectorAll('.frame').forEach(frame => {
                frame.addEventListener('click', () => {
                    const img = frame.querySelector('img').src;
                    const desc = frame.querySelector('p').textContent;
                    const priceMatch = desc.match(/\$\d+/);
                    const price = priceMatch ? priceMatch[0] : 'Unknown';
                    const shop = desc.split('-').pop().trim();
                    showProductModal(img, desc, price, shop);
                });
            });

            document.getElementById('productModal').addEventListener('click', function (e) {
                if (e.target === this) this.style.display = 'none';
            });
        });
document.getElementById('userIcon').addEventListener('click', function() {
  window.location.href = 'newpage.html';
});