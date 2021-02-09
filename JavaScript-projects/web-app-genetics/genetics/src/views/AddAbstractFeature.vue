<template lang="">
  <div>
    <h1>Ajouter une feature abstraite</h1>
    <form
      id="add_abstract_feature"
      @submit.prevent="checkForm"
      action="#"
      method="post"
    >
      <p>
        <label for="af_label">Libellé: </label>
        <input type="text" id="af_label" name="af_label" required />
      </p>

      <p>
        <label for="af_nature">Nature: </label>
        <select name="af_nature" id="af_nature">
          <option value="discrete">Discrète</option>
          <option value="continuous">Continue</option>
        </select>
      </p>

      <p>
        <label for="nb_genes">Nombre de gênes:</label>
        <input type="number" id="af_nbgenes" name="nb_genes" min="1">
      </p>

      <p>
        
      </p>

      <p>
        <input type="submit" value="Ajouter" />
      </p>
    </form>
  </div>
</template>
<script>
export default {
  data() {
    return {};
  },
  methods: {
    checkForm: function(e) {
      console.log("check form", e);
    },
  },
};
</script>
<style lang="scss"></style>
