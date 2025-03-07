import React, { useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { createAccount } from '../services/api'
import './Form.css'

const CreateAccount = () => {
  const [name, setName] = useState('')
  const [initialDeposit, setInitialDeposit] = useState('')
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState(null)
  const navigate = useNavigate()

  const handleSubmit = async (e) => {
    e.preventDefault()
    
    if (!name.trim()) {
      setError('Please enter a name')
      return
    }
    
    const deposit = parseFloat(initialDeposit)
    if (isNaN(deposit) || deposit < 0) {
      setError('Please enter a valid deposit amount')
      return
    }
    
    try {
      setLoading(true)
      const newAccount = await createAccount({ name, balance: deposit })
      navigate(`/account/${newAccount.accountNumber}`)
    } catch (err) {
      setError('Failed to create account. Please try again.')
      console.error(err)
    } finally {
      setLoading(false)
    }
  }

  return (
    <div className="form-container">
      <h1>Create New Account</h1>
      
      {error && <div className="error-message">{error}</div>}
      
      <form onSubmit={handleSubmit}>
        <div className="form-group">
          <label htmlFor="name">Account Holder Name</label>
          <input
            type="text"
            id="name"
            value={name}
            onChange={(e) => setName(e.target.value)}
            disabled={loading}
            required
          />
        </div>
        
        <div className="form-group">
          <label htmlFor="initialDeposit">Initial Deposit ($)</label>
          <input
            type="number"
            id="initialDeposit"
            min="0"
            step="0.01"
            value={initialDeposit}
            onChange={(e) => setInitialDeposit(e.target.value)}
            disabled={loading}
            required
          />
        </div>
        
        <div className="form-actions">
          <button 
            type="button" 
            className="btn btn-secondary"
            onClick={() => navigate('/')}
            disabled={loading}
          >
            Cancel
          </button>
          <button 
            type="submit" 
            className="btn btn-primary"
            disabled={loading}
          >
            {loading ? 'Creating...' : 'Create Account'}
          </button>
        </div>
      </form>
    </div>
  )
}

export default CreateAccount