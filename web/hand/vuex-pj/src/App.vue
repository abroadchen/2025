<template>
  <img alt="Vue logo" src="./assets/logo.png">
  <HelloWorld msg="Welcome to Your Vue.js App"/>
</template>

<script>
import HelloWorld from './components/HelloWorld.vue'

function mapState(stateKeyArr) {
  let obj = {}
  for (let i = 0; i < stateKeyArr.length; i++) {
    let key = stateKeyArr[i]
    obj[key] = function () {
      return this.$store.state[key]
    }
  }
  return obj
}

function mapGetters(stateKeyArr) {
  let obj = {}
  for (let i = 0; i < stateKeyArr.length; i++) {
    let key = stateKeyArr[i]
    obj[key] = function () {
      return this.$store.getters[key]
    }
  }
  return obj
}


export default {
  name: 'App',
  components: {
    HelloWorld
  },
  computed: {
    ...mapState(['name']),
    ...mapGetters(['name']) 
  },
  mounted() {
    
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
