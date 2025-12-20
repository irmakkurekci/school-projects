const Negotiation = require('../models/Negotiation');
const Product = require('../models/Product');

const createNegotiation = async (req, res) => {
  try {
    const { productId, offeredPrice, message } = req.body;

    const product = await Product.findById(productId);
    if (!product) return res.status(404).json({ message: 'Product not found' });

    if (product.owner.toString() === req.user._id.toString()) {
      return res.status(400).json({ message: 'You cannot make an offer on your own product' });
    }

    const negotiation = new Negotiation({
      product: productId,
      buyer: req.user._id,
      offeredPrice,
      message
    });

    const saved = await negotiation.save();
    res.status(201).json(saved);
  } catch (err) {
    res.status(400).json({ message: err.message });
  }
};

const getProductOffers = async (req, res) => {
  try {
    const productId = req.params.productId;

    const product = await Product.findById(productId);
    if (!product) return res.status(404).json({ message: 'Product not found' });

    if (product.owner.toString() !== req.user._id.toString()) {
      return res.status(403).json({ message: 'You are not the owner of this product' });
    }

    const offers = await Negotiation.find({ product: productId }).populate('buyer', 'name email');
    res.json(offers);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

const respondToOffer = async (req, res) => {
  try {
    const negotiation = await Negotiation.findById(req.params.id).populate('product');

    if (!negotiation) return res.status(404).json({ message: 'Negotiation not found' });

    if (negotiation.product.owner.toString() !== req.user._id.toString()) {
      return res.status(403).json({ message: 'You are not authorized to respond to this offer' });
    }

    const { status } = req.body;
    if (!['accepted', 'rejected'].includes(status)) {
      return res.status(400).json({ message: 'Invalid status value' });
    }

    negotiation.status = status;
    await negotiation.save();
    res.json({ message: `Offer ${status}` });
  } catch (err) {
    res.status(400).json({ message: err.message });
  }
};

module.exports = {
  createNegotiation,
  getProductOffers,
  respondToOffer
};
