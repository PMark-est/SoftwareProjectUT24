describe('Extended search test', () => {
  it('should select "string:word" from the dropdown and verify results load within 2 seconds', () => {
    // Visit the page
    cy.visit('http://andmebaas.zapto.org');

    // Activate the "Extended" tab
    cy.get('li.extended > a')
      .should('be.visible')
      .click();

    // Select "string:word" from the dropdown
    cy.get(
      '#query_table > div > div > extended-token > div > div.args > div > extended-and-token > div > div:nth-child(2) > div > extended-cqp-term > div > div.pr-1.inline-block.align-middle.ml-2 > div.arg_selects.word > select.arg_type',
      { timeout: 10000 }
    )
      .should('be.visible')
      .select('word')
      .should('have.value', 'string:word');

    // Enter "raske" into the input field
    cy.get(
      '#query_table > div > div > extended-token > div > div.args > div > extended-and-token > div > div:nth-child(2) > div > extended-cqp-term > div > div.pr-1.inline-block.align-middle.ml-2 > div.arg_val_container > extended-cqp-value > input',
      { timeout: 10000 }
    )
      .should('be.visible') // Ensure the input is visible
      .clear() // Clear any existing value
      .type('raske') // Enter the value
      .should('have.value', 'raske'); // Verify the entered value

    // Submit the search
    cy.get('#content > searchtabs > div > div.tabbable.search_tabs.ng-isolate-scope > div > div.tab-pane.ng-scope.active > div > extended-standard > div > search-submit')
      .should('be.visible')
      .click();

    // Check if results load within 2 seconds
    cy.get('table.results_table.kwic tbody tr.sentence', { timeout: 2000 }) // 2-second timeout
      .should('exist'); // Ensure at least one result is loaded within the time

    // Verify that all rows contain the text "raske"
    cy.get('table.results_table.kwic tbody tr.sentence')
      .then(($rows) => {
        // Skip the first row and iterate over the remaining rows
        cy.wrap($rows.slice(1)).each(($row) => {
          cy.wrap($row).should('contain.text', 'raske');
        });
      });
  });
});
