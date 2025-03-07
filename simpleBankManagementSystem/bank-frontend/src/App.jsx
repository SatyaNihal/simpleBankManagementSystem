import React from 'react'
import { BrowserRouter, Routes, Route } from 'react-router-dom'
import Dashboard from './components/Dashboard'
import NavBar from './components/NavBar'
import CreateAccount from './components/CreateAccount'
import AccountDetails from './components/AccountDetails'
import './App.css'

function App() {
  return (
    <BrowserRouter>
      <div className="app">
        <NavBar />
        <main className="main-content">
          <Routes>
            <Route path="/" element={<Dashboard />} />
            <Route path="/create-account" element={<CreateAccount />} />
            <Route path="/account/:id" element={<AccountDetails />} />
          </Routes>
        </main>
        <footer className="footer">
          <p>© SNK's 2025 Banking System</p>
        </footer>
      </div>
    </BrowserRouter>
  )
}

export default App