const express = require('express');
const router = express.Router();
const verifyToken = require('../middleware/verifyToken');
const { updateProfile, getUserProfile } = require('../controllers/userController');

// Kullanıcının bilgilerini getir
router.get('/me', verifyToken, getUserProfile);

// Kullanıcının bilgilerini güncelle
router.put('/me', verifyToken, updateProfile);

module.exports = router;