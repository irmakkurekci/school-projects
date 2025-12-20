const express = require('express');
const router = express.Router();

const {
  createNegotiation,
  getProductOffers,
  respondToOffer
} = require('../controllers/negotiationController');

const verifyToken = require('../middleware/verifyToken');

// Teklif oluştur
router.post('/', verifyToken, createNegotiation);

// Belirli ürüne gelen teklifler
router.get('/product/:productId', verifyToken, getProductOffers);

// Teklife yanıt (accept / reject)
router.put('/:id/respond', verifyToken, respondToOffer);

module.exports = router;
