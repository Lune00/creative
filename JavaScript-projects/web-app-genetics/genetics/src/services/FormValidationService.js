export class ErrorState {
  constructor(fields) {
    if (!Array.isArray(fields)) {
      return {}
    }
    // eslint-disable-next-line no-unused-vars
    for (const field of fields) {
      this[field] = {
        messages: []
      }
    }
  }
  addMessage(field, msg) {
    if (!Object.prototype.hasOwnProperty.call(this, field)) {
      return
    }
    this[field].messages.push(msg)
  }
  messages(field) {
    if (!Object.prototype.hasOwnProperty.call(this, field)) {
      return
    }
    return this[field].messages
  }
  hasError(field) {
    if (this[field].messages && this[field].messages.length !== 0) {
      return true
    }
    return false
  }
  hasErrors() {
    // eslint-disable-next-line no-unused-vars
    for (const key of Object.keys(this)) {
      if (this.hasError(key)) {
        return true
      }
    }
    return false
  }
  clear() {
    // eslint-disable-next-line no-unused-vars
    for (const key of Object.keys(this)) {
      if (this[key] instanceof ErrorState) {
        this[key].clear()
      }
      if (this[key].messages && this[key].messages.length !== 0) {
        this[key].messages = []
      }
    }
  }
}
