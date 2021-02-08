<template lang="">
  <div>
    <form
      id="add_abstract_feature"
      @submit.prevent="checkForm"
      action="#"
      method="post"
    >
    <p>
    <input
      type="submit"
      value="Submit"
    >
  </p>
    </form>
  </div>
</template>
<script>
export default {
  data() {
    return {
        
    };
  },
  methods: {
    checkForm: function (e) {
      console.log("check form", e);
    },
  },
};
</script>
<style lang="scss"></style>
