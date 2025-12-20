const Store = require('../models/Store');

const createStore = async (req, res) => {
  try {
    const existingStore = await Store.findOne({ owner: req.user._id });
    if (existingStore) {
      return res.status(400).json({ message: 'You already have a store.' });
    }

    const { name, description, logoUrl } = req.body;

    const store = new Store({
      name,
      description,
      logoUrl,
      owner: req.user._id
    });

    const savedStore = await store.save();
    res.status(201).json(savedStore);
  } catch (err) {
    res.status(400).json({ message: err.message });
  }
};

const getAllStores = async (req, res) => {
  try {
    const stores = await Store.find().populate('owner', 'name email');
    res.json(stores);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

const getMyStore = async (req, res) => {
  try {
    const store = await Store.findOne({ owner: req.user._id });
    if (!store) {
      return res.status(404).json({ message: 'Store not found' });
    }
    res.json(store);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

module.exports = {
  createStore,
  getAllStores,
  getMyStore
};
