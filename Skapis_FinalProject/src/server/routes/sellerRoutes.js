const express = require('express');
const router = express.Router();
const { getSellerDashboard } = require('../controllers/sellerController');
const verifyToken = require('../middleware/verifyToken');

// Satıcı paneli
router.get('/dashboard', verifyToken, getSellerDashboard);

module.exports = router;
