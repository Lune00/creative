<template lang="">
  <div>
    <Row
      v-for="(allele, index) in alleles"
      :key="index"
      :allele="allele"
      :index="index"
      @remove_allele="onRemoveAllele"
    ></Row>
    <button type="button" @click="add">Ajouter</button>
  </div>
</template>
<script>
import Row from "@/components/Editor/AllelesEditableListRow.vue";

export default {
  name: "AllelesEditableList",
  components: {
    Row,
  },
  data() {
    return {};
  },
  props: {
    nature: {
      type: String,
      required: true,
    },
    alleles: {
      type: Array,
      required: true,
    },
  },

  methods: {
    add: function() {
      this.$emit("add_allele");
    },
    onRemoveAllele: function(index) {
      this.$emit("remove_allele", index);
    },
  },
};
</script>
<style lang=""></style>
