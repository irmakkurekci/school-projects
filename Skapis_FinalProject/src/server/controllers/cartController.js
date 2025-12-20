const CartItem = require('../models/CartItem');
const Product = require('../models/Product');

const addToCart = async (req, res) => {
  try {
    const { productId, quantity = 1 } = req.body;

    const product = await Product.findById(productId);
    if (!product) return res.status(404).json({ message: 'Product not found' });

    const existing = await CartItem.findOne({ user: req.user._id, product: productId });

    if (existing) {
      existing.quantity += quantity;
      await existing.save();
      return res.json(existing);
    }

    const newItem = new CartItem({
      user: req.user._id,
      product: productId,
      quantity
    });

    const saved = await newItem.save();
    res.status(201).json(saved);
  } catch (err) {
    res.status(400).json({ message: err.message });
  }
};

const getCart = async (req, res) => {
  try {
    const items = await CartItem.find({ user: req.user._id }).populate('product');
    res.json(items);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

const removeFromCart = async (req, res) => {
  try {
    await CartItem.deleteOne({ _id: req.params.id, user: req.user._id });
    res.json({ message: 'Item removed from cart' });
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

const clearCart = async (req, res) => {
  try {
    await CartItem.deleteMany({ user: req.user._id });
    res.json({ message: 'Cart cleared' });
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

module.exports = {
  addToCart,
  getCart,
  removeFromCart,
  clearCart
};
