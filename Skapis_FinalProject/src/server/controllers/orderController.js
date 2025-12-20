const Order = require('../models/Order');
const Product = require('../models/Product');
const CartItem = require('../models/CartItem');

const createOrder = async (req, res) => {
  try {
    const { productId } = req.body;

    const product = await Product.findById(productId);
    if (!product) return res.status(404).json({ message: 'Product not found' });

    const order = new Order({
      buyer: req.user._id,
      product: product._id,
      amount: product.price,
      status: 'paid' // 🎯 Şimdilik ödeme başarılı sayıyoruz
    });

    const saved = await order.save();
    res.status(201).json(saved);
  } catch (err) {
    res.status(400).json({ message: err.message });
  }
};

const getMyOrders = async (req, res) => {
  try {
    const orders = await Order.find({ buyer: req.user._id }).populate('product');
    res.json(orders);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};
const createOrderFromCart = async (req, res) => {
  try {
    const cartItems = await CartItem.find({ user: req.user._id }).populate('product');
    if (cartItems.length === 0) {
      return res.status(400).json({ message: 'Cart is empty' });
    }

    const orders = [];

    for (const item of cartItems) {
      const order = new Order({
        buyer: req.user._id,
        product: item.product._id,
        amount: item.product.price * item.quantity,
        status: 'paid'
      });
      const savedOrder = await order.save();
      orders.push(savedOrder);
    }

    await CartItem.deleteMany({ user: req.user._id });

    res.status(201).json({
      message: 'Checkout successful',
      orders
    });
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

module.exports = {
  createOrder,
  getMyOrders,
  createOrderFromCart
};
