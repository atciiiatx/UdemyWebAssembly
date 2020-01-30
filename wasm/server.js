// Initialize Express database
const express = require('express')
const app = express()

// Serve static files from /public
app.use(express.static('public'))

// Start server
app.listen(4200, () => console.log('Server running of port 4200.'))