const express = require('express');
const router = express.Router();
const {
  getAllProducts,
  getProductById,
  createProduct,
  updateProduct,
  deleteProduct,
  getMyProducts,
  getProductsByStore 
} = require('../controllers/productController');


const verifyToken = require('../middleware/verifyToken');

router.get('/store/:id', getProductsByStore); 

router.get('/my-products', verifyToken, getMyProducts);
// Public routes
router.get('/', getAllProducts);
router.get('/:id', getProductById);

// Protected routes

router.post('/', verifyToken, createProduct);
router.put('/:id', verifyToken, updateProduct);
router.delete('/:id', verifyToken, deleteProduct);


module.exports = router;
