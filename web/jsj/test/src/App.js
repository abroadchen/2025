import React from 'react'
import { Routes, Route } from 'react-router-dom'
import Home from './pages/home'

export default function App() {
    return (
        <div>
            <h1>Header</h1>
            <hr />
            <Routes>
                <Route path='/' element={<Home />} />
            </Routes>
            <hr />
            <h1>Footer</h1>
        </div>
    )
}

