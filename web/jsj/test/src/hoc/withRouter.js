import { useNavigate } from "react-router-dom"

function withRouter(Component) {
    return function WrappedComponent(props) {
        const navigate = useNavigate()
        const router = { navigate }
        return <Component {...props} router={router} />
    }
}

export default withRouter