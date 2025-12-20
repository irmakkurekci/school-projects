const express = require('express');
const router = express.Router();

const {
  createStore,
  getAllStores,
  getMyStore
} = require('../controllers/storeController');

const verifyToken = require('../middleware/verifyToken');

// Create a store (only one per user)
router.post('/', verifyToken, createStore);

// Get all stores (public)
router.get('/', getAllStores);

// Get current user's store
router.get('/me', verifyToken, getMyStore);

module.exports = router;
