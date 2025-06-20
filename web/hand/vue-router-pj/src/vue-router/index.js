import { install } from './index'
import { createMatch } from './create-match'
import {BrowserHistory, HashHistory} from './history'
class VueRouter {
  constructor(options) {
    this.match = createMatch(options.routes || [])
    options.mode = options.mode || 'hash' 
    switch (options.mode) {
      case 'hash':
        this.history = new HashHistory(this)
        break;
      case 'history':
        this.history = new BrowserHistory(this)
        break;
    }

    this.beforeHooks = []

  }

  init(app) {

    const setUpHashListener = () => {
      this.history.listen()
    }


    this.history.transitionTo(this.history.getCurrentLocation(), setUpHashListener)
  
    this.history.locationChangeListen((route) => {
      app._route = route
    })
  
  }

  beforeEach(fn) {
    this.beforeHooks.push(fn)
  }

  push(to) {
    this.history.push(to)
  }

  back() {}
}


VueRouter.install = install


export default VueRouter