import React, { useState } from 'react'
import { Link } from 'react-router-dom'
import './NavBar.css'

const NavBar = () => {
  const [menuOpen, setMenuOpen] = useState(false)

  const toggleMenu = () => {
    setMenuOpen(!menuOpen)
  }

  return (
    <nav className="navbar">
      <div className="navbar-brand">
        <Link to="/">SNK's Banking System</Link>
      </div>
      {/* Hamburger icon visible on small screens */}
      <button 
        className="navbar-toggle" 
        onClick={toggleMenu}
      >
        ☰
      </button>
      <ul className={`navbar-menu ${menuOpen ? 'open' : ''}`}>
        <li>
          <Link to="/" onClick={() => setMenuOpen(false)}>
            Accounts
          </Link>
        </li>
        <li>
          <Link to="/create-account" onClick={() => setMenuOpen(false)}>
            Create Account
          </Link>
        </li>
      </ul>
    </nav>
  )
}

export default NavBar