const express = require('express');
const router = express.Router();

const { createOrder, getMyOrders, createOrderFromCart } = require('../controllers/orderController');
const verifyToken = require('../middleware/verifyToken');

router.post('/from-cart', verifyToken, createOrderFromCart);
// Sipariş oluştur
router.post('/', verifyToken, createOrder);

// Kullanıcının sipariş geçmişi
router.get('/me', verifyToken, getMyOrders);

module.exports = router;
