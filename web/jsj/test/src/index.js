import React from "react";
import ReactDOM from 'react-dom/client'
import App from "./App"
import Menu from "./components/navigator/menu"
import { BrowserRouter } from "react-router-dom"

import 'antd/dist/antd.less'

const root = ReactDOM.createRoot(document.getElementById('root'))
root.render(
  <BrowserRouter>
    <App />
  </BrowserRouter>)