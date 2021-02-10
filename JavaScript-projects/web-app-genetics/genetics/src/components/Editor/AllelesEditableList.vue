<template lang="">
  <div>
    <div v-for="allele in alleles" :key="allele.key">      
      <Row v-bind:allele="allele"></Row>
    </div>
  </div>
</template>
<script>
import Allele from "@/models/Allele.js"
import Row from '@/components/Editor/AllelesEditableListRow.vue'

export default {
  name: "AllelesEditableList",
  components : {
      Row
  },
  data() {
    return {
      alleles: [new Allele("1", "50"), new Allele("2", "100")],
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
