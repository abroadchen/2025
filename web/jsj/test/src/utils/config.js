const DEVELOPMENT = ''
const PRODUCTION = ''

const BASE_URL = process.env.NODE_ENV === 'development' ? DEVELOPMENT : PRODUCTION

const TIMEOUT = 3000

export { BASE_URL, TIMEOUT }