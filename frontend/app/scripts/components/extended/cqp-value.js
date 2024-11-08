/** @format */
import angular from "angular";
import _ from "lodash";
import extendedComponents from "./widgets";

angular.module("korpApp").component("extendedCqpValue", {
  bindings: {
    change: "&",
    attributeDefinition: "<",
    term: "<",
  },
  controller: [
    "$scope",
    "$controller",
    "$compile",
    "$element",
    "$http", // Add $http for AJAX requests
    function ($scope, $controller, $compile, $element, $http) {
      const ctrl = this;

      let prevScope = null;
      let modelChildWatch = null;
      let flagsChildWatch = null;

      ctrl.$onChanges = (changeObj) => {
        if (changeObj.attributeDefinition && ctrl.attributeDefinition) {
          updateComponent(!changeObj.attributeDefinition.isFirstChange());
        }
      };

      function updateComponent(initialized) {
        if (initialized && ctrl.term.flags) {
          delete ctrl.term.flags["c"];
        }

        if (prevScope != null) {
          prevScope.$destroy();
        }

        if (modelChildWatch) {
          modelChildWatch();
          flagsChildWatch();
        }

        const childScope = $scope.$new();
        modelChildWatch = childScope.$watch("model", (val) => {
          ctrl.change({ term: { val } });
        });
        flagsChildWatch = childScope.$watch(
          "orObj.flags",
          (val) => {
            ctrl.change({ term: { flags: val } });
          },
          true
        );

        childScope.orObj = ctrl.term;
        _.extend(childScope, ctrl.attributeDefinition);
        childScope.model = ctrl.term.val;

        // Fetch options dynamically from the server
        const url = `http://andmebaas.zapto.org:8080/lexicon?positional_attribute=${encodeURIComponent(
          ctrl.attributeDefinition.value
        )}`;

        $http.get(url).then(
          function success(response) {
            const optionsArray = response.data.Arguments || [];
            console.log(optionsArray);
            console.log(ctrl.attributeDefinition.value);

            // Populate tmplObj with fetched options
            let tmplObj;
            if (ctrl.attributeDefinition.value === "word") {
              tmplObj = {
                placeholder: "<{{'any' | loc:$root.lang}}>",
                options: optionsArray.map((opt) => ({
                  value: opt,
                  label: opt,
                })),
              };
            } else {
              tmplObj = {
                placeholder: "",
                options: optionsArray.map((opt) => ({
                  value: opt,
                  label: opt,
                })),
              };
            }

            // Attach tmplObj options to childScope to be accessible in the template
            childScope.options = tmplObj.options;
            childScope.placeholder = tmplObj.placeholder;

            // Assign template and controller dynamically
            let template, controller;
            if (ctrl.attributeDefinition["extended_component"]) {
              const def =
                extendedComponents[
                  ctrl.attributeDefinition["extended_component"].name ||
                    ctrl.attributeDefinition["extended_component"]
                ];
              if (_.isFunction(def)) {
                ({ template, controller } = def(tmplObj));
              } else {
                ({ template, controller } = def);
              }
            } else {
              controller = extendedComponents.default.controller;
              if (ctrl.attributeDefinition["extended_template"]) {
                template = ctrl.attributeDefinition["extended_template"];
              } else {
                template = extendedComponents.default.template(tmplObj);
              }
            }

            $controller(controller, { $scope: childScope });
            const tmplElem = $compile(template)(childScope);
            $element.html(tmplElem).addClass("arg_value");

            // Manually trigger a digest cycle to ensure scope update
            $scope.$applyAsync();
          },
          function error(response) {
            console.error("Failed to fetch options:", response);
          }
        );

        prevScope = childScope;
      }
    },
  ],
});


