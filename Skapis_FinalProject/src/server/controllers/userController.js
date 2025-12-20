const User = require('../models/User');
const bcrypt = require('bcryptjs');

const updateProfile = async (req, res) => {
  try {
    const { name, surname, email, phone, birthday, password } = req.body;

    const user = await User.findById(req.user._id);
    if (!user) return res.status(404).json({ message: 'User not found' });

    if (name) user.name = name;
    if (surname) user.surname = surname || user.surname || 'Unknown';
    if (email) user.email = email;
    if (phone) user.phone = phone || user.phone || '0000000000';
    if (birthday) user.birthday = birthday || user.birthday || new Date('2000-01-01');

    if (password) {
      const salt = await bcrypt.genSalt(10);
      user.password = await bcrypt.hash(password, salt);
    }

    const updatedUser = await user.save();

    res.json({
      message: 'Profile updated successfully',
      user: {
        _id: updatedUser._id,
        name: updatedUser.name,
        surname: updatedUser.surname,
        email: updatedUser.email,
        phone: updatedUser.phone,
        birthday: updatedUser.birthday
      }
    });
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};
const getUserProfile = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).select('-password');
    if (!user) return res.status(404).json({ message: 'User not found' });
    res.json(user);
  } catch (err) {
    res.status(500).json({ message: 'Server error' });
  }
};
module.exports = {
  updateProfile,
  getUserProfile
};
