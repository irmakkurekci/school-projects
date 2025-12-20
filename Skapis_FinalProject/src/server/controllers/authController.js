// src/server/controllers/authController.js
const User = require('../models/User');
const jwt = require('jsonwebtoken');

const signup = async (req, res) => {
	console.log('BODY:', req.body);
	
  try {
    const { name, surname, birthday, phone, email, password } = req.body;

    const userExists = await User.findOne({ email });
    if (userExists) return res.status(400).json({ message: 'User already exists' });

    const user = new User({ name, surname, birthday, phone, email, password });
    await user.save();

    const token = jwt.sign({ id: user._id }, process.env.JWT_SECRET, { expiresIn: '7d' });
    res.status(201).json({ token, user: { id: user._id, name: user.name, surname: user.surname, birthday: user.birthday, phone: user.phone, email: user.email } });
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

const signin = async (req, res) => {
  try {
    const { email, password } = req.body;

    const user = await User.findOne({ email });
    if (!user) return res.status(400).json({ message: 'Invalid credentials' });

    const isMatch = await user.comparePassword(password);
    if (!isMatch) return res.status(400).json({ message: 'Invalid credentials' });

    const token = jwt.sign({ id: user._id }, process.env.JWT_SECRET, { expiresIn: '7d' });
    res.json({ token, user: { id: user._id, name: user.name, email: user.email } });
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

module.exports = { signup, signin };
