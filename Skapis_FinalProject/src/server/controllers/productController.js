const Product = require('../models/Product');
const Store = require('../models/Store');

const getAllProducts = async (req, res) => {
  try {
    const products = await Product.find().populate('owner', 'name email');
    res.json(products);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};


const getProductById = async (req, res) => {
  try {
    const product = await Product.findById(req.params.id);
    if (!product) return res.status(404).json({ message: 'Product not found' });
    res.json(product);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

const createProduct = async (req, res) => {
  try {
    const { name, description, price, imageUrl, inStock } = req.body;

    // Kullanıcının mağazasını bul
    const store = await Store.findOne({ owner: req.user._id });
    if (!store) {
      return res.status(400).json({ message: 'User does not have a store.' });
    }

    const product = new Product({
      name,
      description,
      price,
      imageUrl,
      inStock,
      owner: req.user._id,
      store: store._id 
    });

    const saved = await product.save();
    res.status(201).json(saved);
  } catch (err) {
    res.status(400).json({ message: err.message });
  }
};

const updateProduct = async (req, res) => {
  try {
    const product = await Product.findById(req.params.id);

    if (!product) return res.status(404).json({ message: 'Product not found' });

    
    if (product.owner.toString() !== req.user._id.toString()) {
      return res.status(403).json({ message: 'Not authorized to update this product' });
    }

    const updated = await Product.findByIdAndUpdate(req.params.id, req.body, { new: true });
    res.json(updated);
  } catch (err) {
    res.status(400).json({ message: err.message });
  }
};


const deleteProduct = async (req, res) => {
  try {
    const product = await Product.findById(req.params.id);

    if (!product) {
      return res.status(404).json({ message: 'Product not found' });
    }

    if (product.owner && product.owner.toString() !== req.user._id.toString()) {
      return res.status(403).json({ message: 'Not authorized to delete this product' });
    }

    await Product.deleteOne({ _id: req.params.id });

    res.json({ message: 'Product deleted' });
  } catch (err) {
    console.error('❌ Delete Error:', err); 
    res.status(500).json({ message: err.message });
  }
};
const getMyProducts = async (req, res) => {
  try {
    const products = await Product.find({ owner: req.user._id });
    res.json(products);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};
const getProductsByStore = async (req, res) => {
  try {
    const products = await Product.find({ store: req.params.id });
    res.json(products);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

module.exports = {
  getAllProducts,
  getProductById,
  createProduct,
  updateProduct,
  deleteProduct,
  getMyProducts,
  getProductsByStore
	
};

