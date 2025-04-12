import React, { useState, useEffect } from 'react'
import { useParams, useNavigate } from 'react-router-dom'
import { getAccount, depositFunds, withdrawFunds } from '../services/api'
import './AccountDetails.css'

const AccountDetails = () => {
  const { id } = useParams()
  const navigate = useNavigate()
  const [account, setAccount] = useState(null)
  const [amount, setAmount] = useState('')
  const [operation, setOperation] = useState('deposit')
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState(null)
  const [successMessage, setSuccessMessage] = useState(null)

  useEffect(() => {
    const fetchAccountDetails = async () => {
      try {
        setLoading(true)
        const data = await getAccount(id)
        setAccount(data)
        setError(null)
      } catch (err) {
        setError('Failed to fetch account details. Please try again.')
        console.error(err)
      } finally {
        setLoading(false)
      }
    }

    fetchAccountDetails()
  }, [id])

  const handleTransaction = async (e) => {
    e.preventDefault()
    
    const transactionAmount = parseFloat(amount)
    if (isNaN(transactionAmount) || transactionAmount <= 0) {
      setError('Please enter a valid amount')
      return
    }
    
    try {
      setLoading(true)
      setError(null)
      
      let result
      if (operation === 'deposit') {
        result = await depositFunds(id, transactionAmount)
        setSuccessMessage(`Successfully deposited $${transactionAmount.toFixed(2)}`)
      } else {
        result = await withdrawFunds(id, transactionAmount)
        setSuccessMessage(`Successfully withdrew $${transactionAmount.toFixed(2)}`)
      }
      
      setAccount(result)
      setAmount('')
      
      // Clear success message after 3 seconds
      setTimeout(() => {
        setSuccessMessage(null)
      }, 3000)
    } catch (err) {
      setError(operation === 'deposit' 
        ? 'Failed to deposit funds. Please try again.' 
        : 'Failed to withdraw funds. Insufficient balance or other error.')
      console.error(err)
    } finally {
      setLoading(false)
    }
  }

  if (loading && !account) return <div className="loading">Loading account details...</div>
  if (error && !account) return <div className="error">{error}</div>
  if (!account) return <div className="error">Account not found</div>

  return (
    <div className="account-details">
      <div className="account-header">
        <h1>Account Details</h1>
        <button onClick={() => navigate('/')} className="btn btn-secondary">
          Back to Dashboard
        </button>
      </div>
      
      <div className="account-info">
        <div className="info-card">
          <div className="info-label">Account Number</div>
          <div className="info-value">{account.accountNumber}</div>
        </div>
        
        <div className="info-card">
          <div className="info-label">Account Holder</div>
          <div className="info-value">{account.name}</div>
        </div>
        
        <div className="info-card balance">
          <div className="info-label">Current Balance</div>
          <div className="info-value">${account.balance.toFixed(2)}</div>
        </div>
      </div>
      
      <div className="transaction-section">
        <h2>Make a Transaction</h2>
        
        {error && <div className="error-message">{error}</div>}
        {successMessage && <div className="success-message">{successMessage}</div>}
        
        <form onSubmit={handleTransaction}>
          <div className="form-group">
            <label htmlFor="operation">Transaction Type</label>
            <select
              id="operation"
              value={operation}
              onChange={(e) => setOperation(e.target.value)}
              disabled={loading}
            >
              <option value="deposit">Deposit</option>
              <option value="withdraw">Withdraw</option>
            </select>
          </div>
          
          <div className="form-group">
            <label htmlFor="amount">Amount ($)</label>
            <input
              type="number"
              id="amount"
              min="0.01"
              step="0.01"
              value={amount}
              onChange={(e) => setAmount(e.target.value)}
              disabled={loading}
              required
            />
          </div>
          
          <button 
            type="submit" 
            className={`btn ${operation === 'deposit' ? 'btn-deposit' : 'btn-withdraw'}`}
            disabled={loading}
          >
            {loading ? 'Processing...' : operation === 'deposit' ? 'Deposit Funds' : 'Withdraw Funds'}
          </button>
        </form>
      </div>
    </div>
  )
}

export default AccountDetails