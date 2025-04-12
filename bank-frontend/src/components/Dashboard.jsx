import React, { useState, useEffect } from 'react'
import { Link } from 'react-router-dom'
import { fetchAccounts } from '../services/api'
import './Dashboard.css'

const Dashboard = () => {
  const [accounts, setAccounts] = useState([])
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState(null)

  useEffect(() => {
    const getAccounts = async () => {
      try {
        setLoading(true)
        const data = await fetchAccounts()
        setAccounts(data)
        setError(null)
      } catch (err) {
        setError('Failed to fetch accounts. Please try again.')
        console.error(err)
      } finally {
        setLoading(false)
      }
    }

    getAccounts()
  }, [])

  if (loading) return <div className="loading">Loading accounts...</div>
  if (error) return <div className="error">{error}</div>

  return (
    <div className="dashboard">
      <h1>Account Dashboard</h1>
      
      <div className="account-actions">
        <Link to="/create-account" className="btn btn-primary">
          Create New Account
        </Link>
      </div>
      
      {accounts.length === 0 ? (
        <p className="no-accounts">No accounts found. Create one to get started!</p>
      ) : (
        <div className="accounts-table-wrapper">
          <table className="accounts-table">
            <thead>
              <tr>
                <th>Account Number</th>
                <th>Account Holder</th>
                <th>Balance</th>
                <th>Actions</th>
              </tr>
            </thead>
            <tbody>
              {accounts.map(account => (
                <tr key={account.accountNumber}>
                  <td>{account.accountNumber}</td>
                  <td>{account.name}</td>
                  <td>${account.balance.toFixed(2)}</td>
                  <td>
                    <Link to={`/account/${account.accountNumber}`} className="btn btn-small">
                      View Details
                    </Link>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      )}
    </div>
  )
}

export default Dashboard