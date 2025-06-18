import React from 'react'
import { useLocation, useParams } from 'react-router-dom'

export default function Detail() {
  const { id } = useParams()
  const location = useLocation
  const obj = querystring.parse(location.search)
  return (
    <div>
      <h1>Detail</h1>
      <h2>商品 ID: {id}</h2>
    </div>
  )
}
