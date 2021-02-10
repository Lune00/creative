<template lang="">
  <div>
 
      <Row  v-for="(allele, index) in alleles" :key="index" :allele="allele" :index="index"></Row>

    <button type="button" @click="add">Ajouter</button>
  </div>
</template>
<script>
import Allele from "@/models/Allele.js";
import Row from "@/components/Editor/AllelesEditableListRow.vue";

export default {
  name: "AllelesEditableList",
  components: {
    Row,
  },
  data() {
    return {
      alleles: [],
    };
  },
  props: {
    nature: {
      type: String,
      required: true,
    },
  },

  methods: {
      add: function(){
          this.alleles.push(new Allele('',''))
      }
  }
};
</script>
<style lang=""></style>
