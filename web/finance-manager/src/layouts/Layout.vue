<template>
<!--  <div>-->
<!--    我是布局组件,下面是动态内容-->
<!--    <router-view></router-view>-->
<!--  </div>-->
  <el-container>
    <el-aside width="220px">
      <el-menu router default-active="2" class="el-menu-vertical-demo" background-color="#545c64" text-color="#fff" active-text-color="#ffd04b">
        <GAsideMenu v-for="(item, i) in menus" :key="i" :item="item"/>
      </el-menu>
    </el-aside>
    <el-container>
      <el-header>
        <div class="left">
          <GBreadcrumb/>
        </div>
        <div class="right">
          <GDropdown @command="doCommand" :title="'admin'" :items="[{key:'logout', label:'退出'}]"/>
        </div>
      </el-header>
      <el-main>
        <div class="tags-box">
          <el-tag closable @close="delTag(t)" @click="$router.push({name:t.compName})"
          v-for="(t, i) in tags" :key="i">{{t.title}}</el-tag>
        </div>
        <transition name="fade" mode="out-in">
          <keep-alive :max="40" :include="getTagsCompName">
            <router-view/>
          </keep-alive>
        </transition>
      </el-main>
      <el-footer>Footer</el-footer>
    </el-container>
  </el-container>
</template>
<script>
import {mapGetters, mapActions, mapMutations } from 'vuex'

export default {
  methods: {
    ...mapMutations({
      delTag: 'user/delTag'
    }),
    ...mapActions({
      doLogout: 'user/doLogout'
    }),
    async doCommand(e) {
      if (e === 'logout') {
        await this.doLogout()
        window.location.reload()
      }
    }
  },
  components: {

  },
  computed: {
    ...mapGetters({
      menus: 'user/getUserMenus',
      tags: 'user/getTags'
    }),
    getTagsCompName() {
      return this.tags.map(t=>t.compName)
    }
  },
  name: 'Layout',
}
</script>
<style scoped>
.el-header {
  display: flex;
  align-items: center;
  justify-content: space-between;
}
.el-header, .el-footer {
  background-color: #B3C0D1;
  color: #333;
  text-align: center;
  line-height: 60px;
}
.el-aside {
  background-color: #D3DCE6;
  color: #333;
  text-align: center;
  line-height: 200px;
}
.el-main {
  background-color: #E9EEF3;
  color: #333;
  text-align: center;
}
.el-container {
  height: 100%;
}
.el-menu-vertical-demo {
  border: none;
}
.tags-box {
  margin-bottom: 10px;
  text-align: left;
}
.el-tag {
  cursor: pointer;
  margin-right: 4px;
}

.fade-enter-active, .fade-leave-active {
  transition: opacity .5s;
}
.fade-enter, .fade-leave-to {
  opacity: 0;
}
</style>