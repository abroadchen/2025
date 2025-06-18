import React, { useEffect, useState } from 'react'
import axios from 'axios'

export default function Menu() {
  const [menu, setMenu] = useState([])

  const getMenu = async () => {
    try {
        const { data } = await axios.get('')
        setMenu(data.menu)
    } catch (error) {
        throw new Error(error)
    }    
  }

  useEffect(() => {
    getMenu()
  }, [])

  const getMenuItem = (data) => {
    return (
        <ul>
            {
                data.map(item => {
                  return (
                    <li key={item.key}>
                        {item.label}
                        {item.children ? getMenuItem(item.children) : ''}
                    </li>
                  )
                })
            }
        </ul>
    )
  }

  return (
    <div>{getMenuItem(menu)}</div>
  )
}
