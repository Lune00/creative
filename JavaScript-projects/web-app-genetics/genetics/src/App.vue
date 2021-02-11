<template>
  <div id="app">
    <ViewNewAbstractFeature></ViewNewAbstractFeature>
  </div>
</template>

<script>
import ViewNewAbstractFeature from '@/views/Editor/ViewNewAbstractFeature.vue'

export default {
  name: 'App',
  components: {
    ViewNewAbstractFeature
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  /* text-align: center; */
  color: #2c3e50;
  margin-top: 60px;
}
</style>
