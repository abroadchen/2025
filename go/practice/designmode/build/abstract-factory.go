/*
Package designmode

	@author: June
	@since: 2025/7/20
	@desc:
*/
package build

type OrderMainDAO interface {
	SaveOrderMain()
	//DeleteOrderMain()
	//SearchOrderMain()
}

type OrderDetailDAO interface {
	SaveOrderDetail()
}

type DAOFactory interface {
	CreateOrderMainDAO() OrderMainDAO
	CreateOrderDetailDAO() OrderDetailDAO
}

type MySQLMainDAO struct{}

func (m *MySQLMainDAO) DeleteOrderMain() {
	//TODO implement me
	panic("implement me")
}

func (m *MySQLMainDAO) SearchOrderMain() {
	//TODO implement me
	panic("implement me")
}

func (m *MySQLMainDAO) SaveOrderMain() {}

type MySQLDetailDAO struct{}

func (m *MySQLDetailDAO) SaveOrderDetail() {
	//TODO implement me
	panic("implement me")
}

func (m *MySQLDetailDAO) SaveOrderDetailDAO() {}

type MySQLFactory struct{}

func (*MySQLFactory) CreateOrderMainDAO() OrderMainDAO {
	return &MySQLMainDAO{}
}
func (*MySQLFactory) CreateOrderDetailDAO() OrderDetailDAO {
	return &MySQLDetailDAO{}
}

func main() {
	var fac DAOFactory
	fac = &MySQLFactory{}
	fac.CreateOrderMainDAO().SaveOrderMain()
}
