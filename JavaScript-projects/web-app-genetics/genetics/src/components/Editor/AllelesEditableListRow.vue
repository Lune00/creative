<template lang="">
  <div>
    <label :for="inputLabelName()">Label</label>
    <input type="text" :name="inputLabelName()" v-model="allele.key" />

    <label :for="inputLabelValue()">Valeur</label>
    <input type="number" :name="inputLabelValue()" v-model="allele.value" />

    <button type="button" @click="deleteAllele">Supprimer</button>
  </div>
</template>
<script>
import Allele from "@/models/Allele.js";

export default {
  name: "AlleleRow",
  props: {
    allele: {
      type: Object,
      required: true,
      validator: function(allele) {
        return allele instanceof Allele;
      },
    },
    index: {
        type: Number,
        required: true
    }
  },
  methods: {
    inputLabelValue() {
      return "allele-value:" + this.index;
    },
    inputLabelName() {
      return "allele-label:" + this.index;
    },
    deleteAllele() {
        console.log('remove this allele:', this.index)
        this.$emit('event_remove_allele', this.index)
    },
  },
};
</script>
<style lang=""></style>
