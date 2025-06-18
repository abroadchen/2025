import React from 'react'
import routes from './router'
import { useRoutes } from 'react-router-dom'
import { Col, Row } from 'antd'
import { Footer, Header } from 'antd/es/layout/layout'
export default function Admin() {
  const router = useRoutes(routes)
  return (
    <div className="warpper">
      <Row>
        <Col span={4} className='warpper__left'>
          <Navigator />
        </Col>
        <Col span={20} className='warpper__right'>
          <Header />
          <Row className='warpper__right__content'>
            {router}
          </Row>
          <Footer />
        </Col>
      </Row>
    </div>
  )
}
