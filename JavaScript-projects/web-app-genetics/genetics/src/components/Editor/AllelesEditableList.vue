<template lang="">
  <div>
    <div v-for="allele in alleles" :key="allele.key">
      <div>{{ allele.key }}</div>
      <div>{{ allele.value }}</div>
    </div>
  </div>
</template>
<script>
export default {
  name: "AllelesEditableList",
  data() {
    return {
      alleles: [
        {
          key: "foo",
          value: "bar",
        },
         {
          key: "foo",
          value: "bar",
        },
      ],
    };
  },
  props: {
    nature: {
      type: String,
      required: true,
    },
  },
};
</script>
<style lang=""></style>
