const API_URL = 'http://localhost:3001/api';

// Fetch all accounts
export const fetchAccounts = async () => {
  const response = await fetch(`${API_URL}/accounts`);
  
  if (!response.ok) {
    throw new Error(`API error: ${response.status}`);
  }
  
  return response.json();
};

// Get a single account by ID
export const getAccount = async (accountId) => {
  const response = await fetch(`${API_URL}/accounts/${accountId}`);
  
  if (!response.ok) {
    throw new Error(`API error: ${response.status}`);
  }
  
  return response.json();
};

// Create a new account
export const createAccount = async (accountData) => {
  const response = await fetch(`${API_URL}/accounts`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify(accountData),
  });
  
  if (!response.ok) {
    throw new Error(`API error: ${response.status}`);
  }
  
  return response.json();
};

// Deposit funds
export const depositFunds = async (accountId, amount) => {
  const response = await fetch(`${API_URL}/accounts/${accountId}/deposit`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ amount }),
  });
  
  if (!response.ok) {
    throw new Error(`API error: ${response.status}`);
  }
  
  return response.json();
};

// Withdraw funds
export const withdrawFunds = async (accountId, amount) => {
  const response = await fetch(`${API_URL}/accounts/${accountId}/withdraw`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ amount }),
  });
  
  if (!response.ok) {
    throw new Error(`API error: ${response.status}`);
  }
  
  return response.json();
};