<template>
  <div id="app">
    <AddAbstractFeature></AddAbstractFeature>
  </div>
</template>

<script>
import AddAbstractFeature from "@/views/AddAbstractFeature.vue";

export default {
  name: "App",
  components: {
    AddAbstractFeature
  }
};
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
