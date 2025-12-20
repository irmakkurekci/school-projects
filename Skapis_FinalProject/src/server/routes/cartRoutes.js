const express = require('express');
const router = express.Router();

const {
  addToCart,
  getCart,
  removeFromCart,
  clearCart
} = require('../controllers/cartController');

const verifyToken = require('../middleware/verifyToken');

// Sepete ürün ekle
router.post('/', verifyToken, addToCart);

// Sepeti getir
router.get('/', verifyToken, getCart);

// Belirli ürünü sepetten sil
router.delete('/:id', verifyToken, removeFromCart);

// Tüm sepeti temizle
router.delete('/', verifyToken, clearCart);

module.exports = router;
