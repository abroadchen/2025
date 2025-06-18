const initialValue = {
  name: 'xx',
}

export default function reducer(state = initialValue, action) {
  switch (action.type) {
    case 'SET_NAME':
      return {
        ...state,
        name: action.payload,
      }
    default:
      return state
  }
}