const Order = require('../models/Order');
const Product = require('../models/Product');
const Negotiation = require('../models/Negotiation');

const getSellerDashboard = async (req, res) => {
  try {
    // Satıcının ürünlerini bul
    const products = await Product.find({ owner: req.user._id });

    // Ürün ID'lerini topla
    const productIds = products.map(p => p._id);

    // Siparişleri getir
    const orders = await Order.find({ product: { $in: productIds } }).populate('product');

    // Teklifleri getir
    const offers = await Negotiation.find({ product: { $in: productIds } }).populate('buyer product');

    // Toplam gelir
    const totalRevenue = orders.reduce((sum, order) => sum + order.amount, 0);

    res.json({
      totalSales: orders.length,
      totalRevenue,
      soldProducts: orders,
      offers
    });
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

module.exports = {
  getSellerDashboard
};
