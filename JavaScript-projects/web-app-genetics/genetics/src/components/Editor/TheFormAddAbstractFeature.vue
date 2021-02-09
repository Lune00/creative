<template lang="">
  <div>
    <h1>Ajouter une feature abstraite</h1>
    <form
      id="add_abstract_feature"
      @submit.prevent="checkForm"
      action="#"
      method="post"
    >
      <h2>Général</h2>

      <p>
        <label for="af_label">Libellé: </label>
        <input type="text" id="af_label" name="af_label" required />
      </p>

      <p>
        <label for="af_nature">Nature: </label>
        <select v-model="nature" name="af_nature" id="af_nature">
          <option :value="this.discreteNature()">Discrète</option>
          <option :value="this.continuousNature()">Continue</option>
        </select>
      </p>

      <p>
        <label for="nb_genes">Nombre de gênes:</label>
        <input type="number" id="af_nbgenes" name="nb_genes" min="1" />
      </p>

      <h2>Allèles</h2>
      <AllelesEditableList :nature="nature"></AllelesEditableList>

      <h2>Règles de codominance</h2>

      <p>
        <input type="submit" value="Enregistrer" />
      </p>
    </form>
  </div>
</template>
<script>

import AllelesEditableList from "@/components/Editor/AllelesEditableList.vue"
import model from '@/services/model-helpers.js'

export default {
  name: "TheFormAddAbstractFeature",
  components: {
    AllelesEditableList,
  },
  data() {
    return {
      nature: '',
    };
  },
  methods: {
    checkForm: function(e) {
      console.log("check form", e);
    },
    discreteNature(){
      return model.discreteNature()
    },
    continuousNature(){
      return model.continuousNature()
    }
  },
};
</script>
<style lang="scss"></style>
