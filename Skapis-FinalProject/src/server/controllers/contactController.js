// src/server/controllers/contactController.js
const Contact = require('../models/Contact');

const sendMessage = async (req, res) => {
  try {
    const { name, email, message } = req.body;
    if (!name || !email || !message) {
      return res.status(400).json({ message: 'Please fill all the required fields.' });
    }

    const contact = new Contact({ name, email, message });
    const saved = await contact.save();
    res.status(201).json(saved);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

module.exports = { sendMessage };
