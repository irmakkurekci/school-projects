const express = require('express');
const router = express.Router();
const User = require('../models/User');
const jwt = require('jsonwebtoken');

// Kullanıcı kaydı (Register)
router.post('/register', async (req, res) => {
  const { name, surname, birthday, phone, email, password } = req.body;

  try {
    const existing = await User.findOne({ email });
    if (existing) return res.status(400).json({ message: 'Email is already registered' });

    const user = new User({ name, surname, birthday, phone, email, password });
    await user.save();
    res.status(201).json({ message: 'Registiration succesfull' });
  } catch (err) {
    res.status(500).json({ error: 'Registiration unseccesfull' });
  }
});

// Kullanıcı girişi (Login)
router.post('/login', async (req, res) => {
  const { email, password } = req.body;

  try {
    const user = await User.findOne({ email });
    if (!user) return res.status(400).json({ message: 'User is not found' });

    const isMatch = await user.comparePassword(password);
    if (!isMatch) return res.status(400).json({ message: 'Password is incorrect' });

    const token = jwt.sign({ id: user._id }, process.env.JWT_SECRET, { expiresIn: '1h' });
    res.json({ message: 'Login succesfull', token });
  } catch (err) {
    res.status(500).json({ error: 'Login unsuccesfull' });
  }
});

module.exports = router;