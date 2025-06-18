import React from 'react'
import { Outlet } from 'react-router-dom'
import './ui.less'
export default function Ui() {
  return (
    <div className='ui-wrap'>
      <Outlet />
    </div>
  )
}
