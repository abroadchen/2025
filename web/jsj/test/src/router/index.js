import Home from '../pages/home'
import NotFound from '../pages/home/NotFound'

const routes = [
    {
        path: '/',
        element: <Home />
    },
    {
        path: '/home',
        element: <Home />
    },
    {
        path: '/ui',
        element: <Ui />,
        children: [
            {

            }
        ]
    },
    {
        path: '*',
        element: <NotFound />
    }
]

export default routes