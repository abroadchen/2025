import { use, useEffect, useState } from "react";
import { request } from "@/utils/request"
import { Menu } from "antd"
import { useNavigate } from "react-router-dom";
function App() {
  const [menu, setMenu] = useState([])
  const navigate = useNavigate()
  const getMenu = async () => {
    try {
      const data = await request('/menu')
      setMenu(data.menu)
    } catch (error) {
      throw new Error('Failed to fetch menu data')
    }
  }
  useEffect(() => {
    getMenu()
  }, [])

  const click = e => {
    navigate(e.key)
  }

  return (
    <div className="warpper__left__logo">

    </div>
  )
}
